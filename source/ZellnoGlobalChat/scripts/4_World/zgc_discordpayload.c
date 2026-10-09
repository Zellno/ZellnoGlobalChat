class ZGC_DiscordPayload
{
    string username;
    string content;

    void ZGC_DiscordPayload(string webhookUsername, string messageText)
    {
        username = webhookUsername;
        content = messageText;
    }

    protected string EscapeJsonString(string value)
    {
        string escaped = value;

        escaped.Replace("\\", "/");
        escaped.Replace("\"", "'");
        escaped.Replace("\r", " ");
        escaped.Replace("\n", " ");
        escaped.Replace("\t", " ");

        return escaped;
    }

    string ToJson()
    {
        string safeUsername = EscapeJsonString(username);
        string safeContent = EscapeJsonString(content);

        return "{ \"username\": \"" + safeUsername + "\", \"content\": \"" + safeContent + "\", \"allowed_mentions\": { \"parse\": [] } }";
    }
}
