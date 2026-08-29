class ZGC_Settings
{
    bool Enabled = true;
    int MaxMessageLength = 256;
    int CooldownMilliseconds = 2000;
    bool LogAcceptedMessages = true;
    bool LogRejectedMessages = true;

    void Validate()
    {
        MaxMessageLength = Math.Clamp(MaxMessageLength, 32, 512);
        CooldownMilliseconds = Math.Clamp(CooldownMilliseconds, 250, 60000);
    }
}

class ZGC_SettingsManager
{
    protected static ref ZGC_Settings s_Settings;

    static ZGC_Settings Get()
    {
        if (!s_Settings)
        {
            LoadOrCreate();
        }

        return s_Settings;
    }

    static void LoadOrCreate()
    {
        MakeDirectory(ZGC_Constants.SETTINGS_DIRECTORY);
        s_Settings = new ZGC_Settings();

        if (!FileExist(ZGC_Constants.SETTINGS_FILE))
        {
            Save();
            Print(ZGC_Constants.LOG_PREFIX + " Created settings file: " + ZGC_Constants.SETTINGS_FILE);
            return;
        }

        string errorMessage;
        if (!JsonFileLoader<ZGC_Settings>.LoadFile(
            ZGC_Constants.SETTINGS_FILE,
            s_Settings,
            errorMessage
        ))
        {
            Print(ZGC_Constants.LOG_PREFIX + " Failed to load settings; defaults are active. Error: " + errorMessage);
            s_Settings = new ZGC_Settings();
            return;
        }

        if (!s_Settings)
        {
            Print(ZGC_Constants.LOG_PREFIX + " Settings file was empty; defaults are active.");
            s_Settings = new ZGC_Settings();
            return;
        }

        s_Settings.Validate();
        Save();

        Print(
            ZGC_Constants.LOG_PREFIX
            + " Settings loaded: enabled="
            + s_Settings.Enabled.ToString()
            + " maxLength="
            + s_Settings.MaxMessageLength.ToString()
            + " cooldownMs="
            + s_Settings.CooldownMilliseconds.ToString()
        );
    }

    protected static void Save()
    {
        if (!s_Settings)
        {
            s_Settings = new ZGC_Settings();
        }

        s_Settings.Validate();

        string errorMessage;
        if (!JsonFileLoader<ZGC_Settings>.SaveFile(
            ZGC_Constants.SETTINGS_FILE,
            s_Settings,
            errorMessage
        ))
        {
            Print(ZGC_Constants.LOG_PREFIX + " Failed to save settings. Error: " + errorMessage);
        }
    }
}
