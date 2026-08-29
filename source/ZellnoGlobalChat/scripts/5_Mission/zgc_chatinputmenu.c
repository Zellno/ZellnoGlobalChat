modded class ChatInputMenu
{
    protected TextWidget m_ZGC_ChannelIndicator;

    override Widget Init()
    {
        Widget root = super.Init();

        if (layoutRoot)
        {
            m_ZGC_ChannelIndicator = TextWidget.Cast(GetGame().GetWorkspace().CreateWidgets(ZGC_Constants.INDICATOR_LAYOUT, layoutRoot));
        }

        ZGC_RefreshIndicator();
        return root;
    }

    override void Update(float timeslice)
    {
        super.Update(timeslice);

        UAInput toggleInput = GetUApi().GetInputByName(ZGC_Constants.INPUT_TOGGLE);
        if (!toggleInput || !toggleInput.LocalPress())
        {
            return;
        }

        if (m_edit_box)
        {
            string currentText = m_edit_box.GetText();
            int currentLength = currentText.Length();

            if (currentLength > 0 && currentText.Substring(currentLength - 1, 1) == "4")
            {
                m_edit_box.SetText(currentText.Substring(0, currentLength - 1));
                m_edit_box.Update();
            }
        }

        ZGC_ClientState.ToggleChannel();
        ZGC_RefreshIndicator();
    }

    override void OnShow()
    {
        super.OnShow();
        ZGC_RefreshIndicator();
    }

    override void Refresh()
    {
        super.Refresh();
        ZGC_RefreshIndicator();
    }

    override bool OnChange(Widget w, int x, int y, bool finished)
    {
        if (!finished)
        {
            return super.OnChange(w, x, y, finished);
        }

        if (!m_edit_box)
        {
            return super.OnChange(w, x, y, finished);
        }

        string text = m_edit_box.GetText();

        if (text == "")
        {
            return super.OnChange(w, x, y, finished);
        }

        string firstCharacter = text.Substring(0, 1);

        if (firstCharacter == "!" || firstCharacter == "/")
        {
            return super.OnChange(w, x, y, finished);
        }

        if (ZGC_ClientState.IsVicinity())
        {
            return super.OnChange(w, x, y, finished);
        }

        ZGC_SendGlobalMessage(text);

        m_close_timer.Run(0.1, this, "Close");
        GetUApi().GetInputByID(UAPersonView).Supress();

        return true;
    }

    protected void ZGC_RefreshIndicator()
    {
        if (!m_ZGC_ChannelIndicator)
        {
            return;
        }

        m_ZGC_ChannelIndicator.SetText(ZGC_ClientState.GetLabel());
        m_ZGC_ChannelIndicator.Show(true);
    }

    protected void ZGC_SendGlobalMessage(string text)
    {
        if (!GetGame().IsMultiplayer())
        {
            string playerName;
            GetGame().GetPlayerName(playerName);
            ZGC_ClientState.AddGlobalLine(playerName, text);
            return;
        }

        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (!player)
        {
            return;
        }

        Param1<string> payload = new Param1<string>(text);

        GetGame().RPCSingleParam(player, ZGC_Constants.RPC_SEND_GLOBAL, payload, true);
    }
}
