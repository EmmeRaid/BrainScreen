using System;
using System.Runtime.InteropServices;

class Program
{
    [DllImport("user32.dll")]
    public static extern int EnumDisplaySettings(string deviceName, int modeNum, ref DEVMODE devMode);

    [DllImport("user32.dll")]
    public static extern int ChangeDisplaySettings(ref DEVMODE devMode, int flags);

    [StructLayout(LayoutKind.Sequential)]
    public struct DEVMODE
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string dmDeviceName;
        public short dmSpecVersion;
        public short dmDriverVersion;
        public short dmSize;
        public short dmDriverExtra;
        public int dmFields;
        public int dmPositionX;
        public int dmPositionY;
        public int dmDisplayOrientation; // Ruota 0 = orizzontale, 1 = verticale
        public int dmDisplayFixedOutput;
    }

    const int ENUM_CURRENT_SETTINGS = 0x00000001;
    const int CDS_UPDATEREGISTRY = 0x00000001;
    const int DMDO_DEFAULT = 0;
    const int DMDO_90 = 1;
    const int DMDO_180 = 2;
    const int DMDO_270 = 3;

    static void Main()
    {
        DEVMODE devMode = new DEVMODE();
        devMode.dmSize = (short)Marshal.SizeOf(typeof(DEVMODE));

        // Ottieni le impostazioni correnti del display
        EnumDisplaySettings(null, ENUM_CURRENT_SETTINGS, ref devMode);

        // Cambia l'orientamento del display
        devMode.dmDisplayOrientation = DMDO_90; // 90 gradi per orientamento verticale
        ChangeDisplaySettings(ref devMode, CDS_UPDATEREGISTRY);
        Console.WriteLine("Display ruotato a 90 gradi (verticale).");
    }
}
