modded class MissionGameplay
{
    void MissionGameplay()
    {
        ZGC_ClientState.Reset();

        if (!GetGame().IsDedicatedServer())
        {
            GetDayZGame().Event_OnRPC.Insert(ZGC_OnRPC);
        }
    }

    void ~MissionGameplay()
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
        if (rpcType != ZGC_Constants.RPC_RECEIVE_GLOBAL)
        {
            return;
        }

        if (GetGame().IsServer())
        {
            return;
        }

        PlayerBase localPlayer = PlayerBase.Cast(GetGame().GetPlayer());

        if (target && target != localPlayer)
        {
            return;
        }

        Param2<string, string> payload;
        if (!ctx.Read(payload))
        {
            return;
        }

        string senderName = payload.param1;
        string message = payload.param2;

        if (message == "")
        {
            return;
        }

        if (senderName.Length() > 128 || message.Length() > 512)
        {
            return;
        }

        ZGC_ClientState.AddGlobalLine(senderName, message);
    }
}
