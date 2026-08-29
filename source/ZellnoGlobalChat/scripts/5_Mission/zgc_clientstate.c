class ZGC_ClientState
{
    protected static int s_Channel = ZGC_Constants.CHANNEL_VICINITY;

    static void Reset()
    {
        s_Channel = ZGC_Constants.CHANNEL_VICINITY;
    }

    static bool IsGlobal()
    {
        return s_Channel == ZGC_Constants.CHANNEL_GLOBAL;
    }

    static bool IsVicinity()
    {
        return s_Channel == ZGC_Constants.CHANNEL_VICINITY;
    }

    static void ToggleChannel()
    {
        if (IsGlobal())
        {
            s_Channel = ZGC_Constants.CHANNEL_VICINITY;
        }
        else
        {
            s_Channel = ZGC_Constants.CHANNEL_GLOBAL;
        }
    }

    static string GetLabel()
    {
        if (IsGlobal())
        {
            return ZGC_Constants.LABEL_GLOBAL;
        }

        return ZGC_Constants.LABEL_VICINITY;
    }

    static void AddGlobalLine(string senderName, string message)
    {
        MissionGameplay mission = MissionGameplay.Cast(GetGame().GetMission());
        if (!mission || !mission.m_Chat)
        {
            return;
        }

        string shownSender = "[GLOBAL]";

        if (senderName != "")
        {
            shownSender = "[GLOBAL] " + senderName;
        }

        ChatMessageEventParams chatParams = new ChatMessageEventParams(CCDirect, shownSender, message, "");

        mission.m_Chat.Add(chatParams);
    }
}
