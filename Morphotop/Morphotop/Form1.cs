using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Morphotop
{
    public unsafe partial class Form1 : Form
    {

        public Form1()
        {
            InitializeComponent();
            //BDS_Callback callback = Callback;

        }
        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
        public struct BDS_Image
        {
            public unsafe uint m_magic;
            public unsafe uint m_version;
            public unsafe uint m_width;
            public unsafe uint m_height;
            public unsafe uint m_flags;
            public IntPtr m_image;
            public unsafe uint m_count;
            public unsafe uint m_checksum;
            public unsafe fixed byte m_rfu[25];
        }
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public unsafe delegate int BDS_Callback(IntPtr i_i_deviceHandle,
                                   BDS_Image* i_p_currentImage, IntPtr i_p_inputData,
                                    IntPtr o_p_outputData, IntPtr i_p_userData);

        public  unsafe int CallbackPointer(IntPtr i_i_deviceHandle, BDS_Image* i_p_currentImage, IntPtr i_p_inputData,
                                    IntPtr o_p_outputData, IntPtr i_p_userData)
        {
            try
            {
                uint size = i_p_currentImage->m_width * i_p_currentImage->m_height;
                byte[] data = new byte[size];
                byte[] height = new byte[i_p_currentImage->m_height];
                byte[] width = new byte[i_p_currentImage->m_width];
                IntPtr pointer = Marshal.AllocHGlobal(data.Length);
                Marshal.Copy(i_p_currentImage->m_image, data, 0, data.Length);
                Marshal.FreeHGlobal(pointer);

                 SetPicture(pictureBox1, ConvertToBitmap(data, width.Length, height.Length));
            }
            catch
            {
            }
            return 0;
        }
        private  void SetPicture(PictureBox img, Bitmap bmp)
        {
            try
            {
                if (img.InvokeRequired)
                {
                    img.Invoke(new MethodInvoker(
                    delegate()
                    {
                        pictureBox1.Image = bmp;
                    }));
                }
                else
                {
                    pictureBox1.Image = bmp;
                }
            }
            catch
            {
            }
        }
        public void Initialize()
        {


            // int res5 = OpenBioDevice(i_p_handle, 0, out device_handle, user_data);
        }
        private void Capture_Click(object sender, EventArgs e)
        {




            int p = BDS_SetParametersForDirectMode(i_p_handle, 1);
            BDS_Image* resdet = BDS_GetDirectImage(i_p_handle, 0, 5000);
            uint size = resdet->m_width * resdet->m_height;
            byte[] data = new byte[size];
            byte[] height = new byte[resdet->m_height];
            byte[] width = new byte[resdet->m_width];
            if (data.Length != null)
            {
                IntPtr pointer = Marshal.AllocHGlobal(data.Length);
                try
                {
                    Marshal.Copy(resdet->m_image, data, 0, data.Length);
                    Marshal.FreeHGlobal(pointer);
                    File.WriteAllBytes("test",data);
                    Bitmap bmp =ConvertToBitmap(data, width.Length, height.Length);
                    bmp.Save(Directory.GetCurrentDirectory()+"\\test.jpg");
                    pictureBox2.Image = bmp;
                }
                catch
                {

                }
            }
           
        }
        private Bitmap ConvertToBitmap(byte[] image_data,int width,int height)
        {
            try
            {
                int Width = width;
                int Height = height;
                var b = new Bitmap(Width, Height, PixelFormat.Format8bppIndexed);

                ColorPalette ncp = b.Palette;
                for (int i = 0; i < 256; i++)
                    ncp.Entries[i] = Color.FromArgb(255, i, i, i);
                b.Palette = ncp;
                var BoundsRect = new Rectangle(0, 0, Width, Height);
                BitmapData bmpData = b.LockBits(BoundsRect,
                                                ImageLockMode.WriteOnly,
                                                b.PixelFormat);

                IntPtr ptr = bmpData.Scan0;

                int bytes = width * b.Height;
                var rgbValues = new byte[bytes];
                Marshal.Copy(image_data, 0, ptr, bytes);
                b.UnlockBits(bmpData);
                return b;
            }
            catch
            {
                return null;
            }
        }



        private void Form1_Load(object sender, EventArgs e)
        {
            Initialize(textBox1);
        }



       private IntPtr i_p_handle;
        public void Initialize(TextBox result)
        {
            i_p_handle = IntPtr.Zero;
            IntPtr o_pp_procaddress = IntPtr.Zero;
            IntPtr o_p_interfaceTable = IntPtr.Zero;
            IntPtr o_i_interfaceTable_count = IntPtr.Zero;
            IntPtr o_i_dllVersion = IntPtr.Zero;
        
            IntPtr o_p_deviceCount = IntPtr.Zero;
            IntPtr device_handle = IntPtr.Zero;
            IntPtr img2 = IntPtr.Zero;
            IntPtr r = IntPtr.Zero;
            int user_data = 300;
            int re = 0;
            result.AppendText("Loading Library......." + Environment.NewLine);
            re = LoadLib(Directory.GetCurrentDirectory() + "\\SDKServices.dll", out i_p_handle);
            if (re == 0)
            {
                result.AppendText("Library Loaded No ERRORS" + Environment.NewLine);
                result.AppendText("Resolving interface" + Environment.NewLine);
                re = resolveInterface(Directory.GetCurrentDirectory() + "\\SDKServices.dll", o_pp_procaddress, out o_p_interfaceTable, out o_i_interfaceTable_count, out o_i_dllVersion);
                if (re == 0)
                {
                    result.AppendText("Interface resolved" + Environment.NewLine);
                    result.AppendText("Enumerating devices" + Environment.NewLine);
                    re = EnumerateUsableBiometricDevices(i_p_handle, out o_p_deviceCount);
                        OpenBioDevice(i_p_handle,0,out r,user_data);
                        SetupLiveMode(0,i_p_handle);
                    if (re == 0)
                    {
                        result.ForeColor = Color.Black;
                        result.AppendText("device enumerated" + Environment.NewLine);
                    }
                    else
                    {
                        result.AppendText("device could not be enumerated" + Environment.NewLine);
                    }
                }
                else
                {
                    result.AppendText("Interface could not be resolved" + Environment.NewLine);
                }
            }
            else
            {
                result.ForeColor = Color.Black;
                result.AppendText("could not load library" + Environment.NewLine);
            }
        }
        public void OpenDevice(TextBox result, IntPtr i_p_handle, IntPtr o_p_deviceHandle, int i_p_userData)
        {
            int resu = OpenBioDevice(i_p_handle, 0, out o_p_deviceHandle, i_p_userData);
            if (resu == 0)
            {
                result.AppendText("Biometric Device Opened" + Environment.NewLine);
            }
            else
            {
                result.AppendText("Could not open Biometric device" + Environment.NewLine);
            }
        }

        public void CloseDevice(TextBox result, IntPtr i_p_handle, int o_p_deviceHandle)
        {
            int resu = CloseBioDevice(i_p_handle, o_p_deviceHandle);
            if (resu == 0)
            {
                result.ForeColor = Color.Black;
                result.AppendText("Biometric Device Closed" + Environment.NewLine);
            }
            else
            {
                result.ForeColor = Color.Red;
                result.AppendText("Could not close Biometric device" + Environment.NewLine);
            }
        }
        public BDS_Callback callback1;
        public void SetupLiveMode(int SamplingMode, IntPtr i_p_handle)
        {
             callback1 = new BDS_Callback(CallbackPointer);
             int res = BDS_DefineLiveProcess(i_p_handle, SamplingMode, callback1);
        }
        [DllImport("SSB.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public extern static int LoadLib(String path, out IntPtr i_p_handle);

        [DllImport("SSB.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int GProcAddress(IntPtr i_p_handle, string i_pc_method, out IntPtr o_pp_procaddress);

        [DllImport("SSB.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public extern static int resolveInterface(String path, IntPtr i_i_dllType, out IntPtr o_p_interfaceTable, out IntPtr o_i_interfaceTable_count, out IntPtr o_i_dllVersion);


        [DllImport("SSB.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public extern static int EnumerateUsableBiometricDevices(IntPtr path, out IntPtr o_p_deviceCount);


        [DllImport("SSB.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public extern static int OpenBioDevice(IntPtr path, int i_i_deviceIndex, out IntPtr o_p_deviceHandle, int i_p_userData);


        [DllImport("SSB.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public extern static int CloseBioDevice(IntPtr path, int i_i_deviceHandle);

        [DllImport("SSB.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public extern static int SetDetectionMode(IntPtr path, IntPtr i_i_deviceHandle, int i_i_detectionMode, int i_i_fingerNumber);
        [DllImport("SSB.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern unsafe static BDS_Image* BDS_GetDirectImage(IntPtr path, int i_i_deviceHandle, ulong i_l_timeout);
        [DllImport("SSB.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public extern static int BDS_SetParametersForDirectMode(IntPtr hadle, int sample);
        [DllImport("SSB.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public extern static int BDS_SetParametersForDirectMode(IntPtr path, IntPtr i_i_deviceHandle, int i_i_samplingMode);
        [DllImport("SSB.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public extern static int BDS_DefineLiveProcess(IntPtr l_p_handle, int a, BDS_Callback c);

        [DllImport("SSB.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public extern static int BDS_DefineLiveProcess(int l_p_handle, BDS_Callback bds);

        private void Close_Click(object sender, EventArgs e)
        {
            CloseDevice(textBox1, i_p_handle, 0);
        }
        IEnumerable<Rectangle> FindImageTiles(Bitmap compositeImage)
        {
            var result = new List<Rectangle>();

            // Scan for a non-empty region that hasn't already been "captured"
            for (var x = 0; x < compositeImage.Width; x++)
            {
                for (var y = 0; y < compositeImage.Height; y++)
                {
                    // Only process the pixel if we don't have a rectangle that
                    // already contains this and if it's not empty
                    if (!result.Any(r => r.Contains(x, y))
                        && compositeImage.GetPixel(x, y).A != 0)
                    {
                        // Now that we've found a point, create a rectangle
                        // surrounding that point, then expand outward until
                        // we have a bounding rectangle that doesn't intersect
                        // with the tile
                        var rect = new Rectangle(x - 1, y - 1, 2, 2);
                        bool foundBounds = false;
                        while (!foundBounds)
                        {
                            var xRange = Enumerable.Range(rect.Left, rect.Right)
                                .Where(px => px >= 0 && px < compositeImage.Width);
                            var yRange = Enumerable.Range(rect.Top, rect.Bottom)
                                .Where(py => py >= 0 && py < compositeImage.Height);

                            // Adjust the top
                            if (rect.Top >= 0
                                && xRange
                                    .Select(bx => compositeImage.GetPixel(bx, rect.Top))
                                    .Any(p => p.A != 0))
                            {
                                rect.Y--;
                                rect.Height++;
                            }
                            else if (rect.Bottom < compositeImage.Height
                                && xRange
                                    .Select(bx => compositeImage.GetPixel(bx, rect.Bottom))
                                    .Any(p => p.A != 0))
                            {
                                rect.Height++;
                            }
                            else if (rect.Left >= 0
                                && yRange
                                    .Select(by => compositeImage.GetPixel(rect.Left, by))
                                    .Any(p => p.A != 0))
                            {
                                rect.X--;
                                rect.Width++;
                            }
                            else if (rect.Right < compositeImage.Width
                                && yRange
                                    .Select(by => compositeImage.GetPixel(rect.Right, by))
                                    .Any(p => p.A != 0))
                            {
                                rect.Width++;
                            }
                            else
                            {
                                foundBounds = true;
                            }
                        }
                        result.Add(rect);
                    }
                }
            }

            return result;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            IEnumerable<Rectangle> rec = FindImageTiles((Bitmap)pictureBox2.Image);
            Image img = pictureBox2.Image;
            Graphics newGraphics = Graphics.FromImage(img);
            foreach(Rectangle r in rec){
                newGraphics.DrawRectangle(new Pen(Color.Black, 2), r);
            }
        }
    }
}
