modded class MissionServer
{
    protected ref map<string, int> m_ZGC_LastAcceptedByIdentity;
    protected ref map<string, int> m_ZGC_LastVicinityAuditByIdentity;

    void MissionServer()
    {
        m_ZGC_LastAcceptedByIdentity = new map<string, int>;
        m_ZGC_LastVicinityAuditByIdentity = new map<string, int>;

        ZGC_SettingsManager.LoadOrCreate();
        GetDayZGame().Event_OnRPC.Insert(ZGC_OnRPC);

        Print(ZGC_Constants.LOG_PREFIX + " Server RPC handler initialized.");
    }

    void ~MissionServer()
    {
        if (GetDayZGame())
        {
            GetDayZGame().Event_OnRPC.Remove(ZGC_OnRPC);
        }
    }

    protected void ZGC_OnRPC(
        PlayerIdentity sender,
        Object target,
        int rpcType,
        ParamsReadContext ctx
    )
    {
        if (rpcType == ZGC_Constants.RPC_AUDIT_VICINITY)
        {
            ZGC_OnVicinityAudit(sender, target, ctx);
            return;
        }

        if (rpcType != ZGC_Constants.RPC_SEND_GLOBAL)
        {
            return;
        }

        if (!GetGame().IsServer())
        {
            return;
        }

        ZGC_Settings settings = ZGC_SettingsManager.Get();
        if (!settings || !settings.Enabled)
        {
            ZGC_LogRejected(sender, "global chat disabled");
            return;
        }

        if (!sender)
        {
            ZGC_LogRejected(NULL, "missing sender identity");
            return;
        }

        PlayerBase targetPlayer = PlayerBase.Cast(target);
        if (!targetPlayer)
        {
            ZGC_LogRejected(sender, "invalid RPC target");
            return;
        }

        PlayerIdentity targetIdentity = targetPlayer.GetIdentity();
        if (!targetIdentity)
        {
            ZGC_LogRejected(sender, "target has no identity");
            return;
        }

        string senderId = sender.GetId();
        if (senderId == "" || targetIdentity.GetId() != senderId)
        {
            ZGC_LogRejected(sender, "sender and target identity mismatch");
            return;
        }

        Param1<string> payload;
        if (!ctx.Read(payload))
        {
            ZGC_LogRejected(sender, "unreadable payload");
            return;
        }

        string message = payload.param1;
        message = message.Trim();

        if (message == "")
        {
            ZGC_LogRejected(sender, "empty message");
            return;
        }

        if (message.IndexOf("\r") != -1 || message.IndexOf("\n") != -1 || message.IndexOf("\t") != -1)
        {
            ZGC_LogRejected(sender, "control characters");
            return;
        }

        if (message.Length() > settings.MaxMessageLength)
        {
            ZGC_LogRejected(sender, "message too long");
            return;
        }

        int now = GetGame().GetTime();
        int lastAccepted;

        if (m_ZGC_LastAcceptedByIdentity.Find(senderId, lastAccepted))
        {
            int elapsed = now - lastAccepted;

            if (elapsed >= 0 && elapsed < settings.CooldownMilliseconds)
            {
                ZGC_LogRejected(sender, "cooldown");
                return;
            }
        }

        m_ZGC_LastAcceptedByIdentity.Set(senderId, now);

        string senderName = sender.GetName();
        ZGC_Broadcast(senderName, message);

        if (settings.LogAcceptedMessages)
        {
            Print(ZGC_Constants.LOG_PREFIX + " accepted" + " id=" + senderId + " name=" + senderName + " message=" + message);
        }

        string discordContent = "[GLOBAL] " + senderName + ": " + message;

        ZGC_GetDiscordWebhook().Send(settings.DiscordGlobalWebhookUrl, settings.DiscordWebhookUsername, "GLOBAL", discordContent);
    }

    protected void ZGC_Broadcast(string senderName, string message)
    {
        array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);

        Param2<string, string> outgoing = new Param2<string, string>(senderName, message);

        for (int i = 0; i < players.Count(); i++)
        {
            PlayerBase player = PlayerBase.Cast(players.Get(i));
            if (!player)
            {
                continue;
            }

            PlayerIdentity recipient = player.GetIdentity();
            if (!recipient)
            {
                continue;
            }

            GetGame().RPCSingleParam(player, ZGC_Constants.RPC_RECEIVE_GLOBAL, outgoing, true, recipient);
        }
    }

    protected void ZGC_OnVicinityAudit(
        PlayerIdentity sender,
        Object target,
        ParamsReadContext ctx
    )
    {
        if (!GetGame().IsServer() || !sender)
        {
            return;
        }

        ZGC_Settings settings = ZGC_SettingsManager.Get();
        if (!settings || !settings.Enabled)
        {
            return;
        }

        PlayerBase targetPlayer = PlayerBase.Cast(target);
        if (!targetPlayer)
        {
            return;
        }

        PlayerIdentity targetIdentity = targetPlayer.GetIdentity();
        if (!targetIdentity)
        {
            return;
        }

        string senderId = sender.GetId();
        if (senderId == "" || targetIdentity.GetId() != senderId)
        {
            return;
        }

        Param1<string> payload;
        if (!ctx.Read(payload))
        {
            return;
        }

        string message = payload.param1;
        message = message.Trim();

        if (message == "")
        {
            return;
        }

        if (message.IndexOf("\r") != -1 || message.IndexOf("\n") != -1 || message.IndexOf("\t") != -1)
        {
            return;
        }

        if (message.Length() > settings.MaxMessageLength)
        {
            return;
        }

        int now = GetGame().GetTime();
        int lastAudit;

        if (m_ZGC_LastVicinityAuditByIdentity.Find(senderId, lastAudit))
        {
            int elapsed = now - lastAudit;

            if (elapsed >= 0 && elapsed < settings.VicinityAuditCooldownMilliseconds)
            {
                return;
            }
        }

        m_ZGC_LastVicinityAuditByIdentity.Set(senderId, now);

        string senderName = sender.GetName();

        if (settings.LogAcceptedMessages)
        {
            Print(ZGC_Constants.LOG_PREFIX + " vicinity-audit" + " id=" + senderId + " steamId=" + sender.GetPlainId() + " name=" + senderName + " position=" + targetPlayer.GetPosition().ToString() + " message=" + message);
        }

        string discordContent = "[VICINITY] " + senderName + ": " + message;

        ZGC_GetDiscordWebhook().Send(settings.DiscordVicinityWebhookUrl, settings.DiscordWebhookUsername, "VICINITY", discordContent);
    }

    protected void ZGC_LogRejected(
        PlayerIdentity identity,
        string reason
    )
    {
        ZGC_Settings settings = ZGC_SettingsManager.Get();
        if (!settings || !settings.LogRejectedMessages)
        {
            return;
        }

        string identityId = "unknown";
        string identityName = "unknown";

        if (identity)
        {
            identityId = identity.GetId();
            identityName = identity.GetName();
        }

        Print(ZGC_Constants.LOG_PREFIX + " rejected" + " id=" + identityId + " name=" + identityName + " reason=" + reason);
    }
}
