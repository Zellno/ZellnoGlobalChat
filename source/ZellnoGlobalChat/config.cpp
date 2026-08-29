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
        version = "0.1.0-dev";
        type = "mod";

        inputs = "ZellnoGlobalChat\inputs.xml";

        dependencies[] =
        {
            "Game",
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
