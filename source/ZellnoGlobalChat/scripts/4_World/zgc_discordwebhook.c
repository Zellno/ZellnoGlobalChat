class ZGC_DiscordWebhook
{
    protected static const string DISCORD_BASE_URL = "https://discord.com/api/webhooks/";
    protected ref ZGC_DiscordCallback m_Callback;

    void ZGC_DiscordWebhook()
    {
        m_Callback = new ZGC_DiscordCallback();

        if (!GetRestApi())
        {
            CreateRestApi();
        }
    }

    void Send(
        string webhookUrl,
        string webhookUsername,
        string channel,
        string messageText
    )
    {
        if (webhookUrl == "")
        {
            return;
        }

        if (webhookUrl.IndexOf(DISCORD_BASE_URL) != 0)
        {
            Print(ZGC_Constants.LOG_PREFIX + " Discord webhook rejected: invalid host for channel=" + channel);
            return;
        }

        if (webhookUsername == "")
        {
            webhookUsername = "Zellno Global Chat";
        }

        ZGC_DiscordPayload payload = new ZGC_DiscordPayload(webhookUsername, messageText);

        RestContext context = GetRestApi().GetRestContext(webhookUrl);
        context.SetHeader("application/json");
        context.POST(m_Callback, "", payload.ToJson());
    }
}

ref ZGC_DiscordWebhook g_ZGC_DiscordWebhook;

static ZGC_DiscordWebhook ZGC_GetDiscordWebhook()
{
    if (!g_ZGC_DiscordWebhook)
    {
        g_ZGC_DiscordWebhook = new ZGC_DiscordWebhook();
    }

    return g_ZGC_DiscordWebhook;
}
