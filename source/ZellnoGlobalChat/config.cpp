class CfgPatches
{
    class ZellnoGlobalChat
    {
        units[] = {};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] =
        {
            "DZ_Data",
            "DZ_Scripts"
        };
    };
};

class CfgMods
{
    class ZellnoGlobalChat
    {
        dir = "ZellnoGlobalChat";
        name = "Zellno Global Chat";
        author = "Zellno";
        version = "0.2.0-alpha";
        type = "mod";

        inputs = "ZellnoGlobalChat\inputs.xml";

        dependencies[] =
        {
            "Game",
            "World",
            "Mission"
        };

        class defs
        {
            class gameScriptModule
            {
                value = "";
                files[] =
                {
                    "ZellnoGlobalChat/scripts/3_Game"
                };
            };

            class worldScriptModule
            {
                value = "";
                files[] =
                {
                    "ZellnoGlobalChat/scripts/4_World"
                };
            };

            class missionScriptModule
            {
                value = "";
                files[] =
                {
                    "ZellnoGlobalChat/scripts/5_Mission"
                };
            };
        };
    };
};
