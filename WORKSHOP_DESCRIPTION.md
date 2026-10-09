[h1]Zellno Global Chat[/h1]

Small and independent global text chat for DayZ servers.
Vanilla Vicinity Chat remains available and unchanged.

[h2]Features[/h2]

[list]
[*]Server-wide Global Chat between connected players.
[*]Vanilla Vicinity Chat preserved for nearby communication.
[*]Clear VICINITY and GLOBAL channel indicator.
[*]Configurable channel-toggle input with Numpad 4 as default.
[*]Server-authoritative player names.
[*]Per-player Global Chat cooldown.
[*]Server-side identity, target, length and content validation.
[*]Accepted and rejected request logging.
[*]Optional Discord webhook forwarding.
[*]Separate Discord channels for GLOBAL and VICINITY logs.
[*]Simple JSON server configuration.
[/list]

[h2]Usage[/h2]

[list]
[*]Press Enter to open the normal DayZ chat input.
[*]VICINITY is selected by default.
[*]Press Numpad 4 while chat is open to alternate VICINITY and GLOBAL.
[*]Press Enter to send through the selected channel.
[/list]

Vicinity means nearby players only. Global reaches every connected player.
The toggle action can be remapped in the DayZ controls.

[h2]Server configuration[/h2]

The server creates:

[code]$profile:ZellnoGlobalChat/settings.json[/code]

Defaults:

[list]
[*]Global Chat enabled.
[*]Maximum server-side message length: 256 characters.
[*]Per-player Global Chat cooldown: 2000 milliseconds.
[*]Per-player VICINITY audit cooldown: 500 milliseconds.
[*]Accepted and rejected request logging enabled.
[*]Discord forwarding disabled until webhook URLs are configured.
[*]Discord webhook username: Zellno Global Chat.
[/list]

Optional Discord and audit settings:

[code]VicinityAuditCooldownMilliseconds[/code]
[code]DiscordGlobalWebhookUrl[/code]
[code]DiscordVicinityWebhookUrl[/code]
[code]DiscordWebhookUsername[/code]

GLOBAL and VICINITY can use separate Discord webhook channels.
Webhook URLs remain in the server profile and are not embedded in the mod.
Discord allowed mentions are disabled.

[h2]Compatibility[/h2]

[list]
[*]DayZ 1.29
[*]ZenModCore chat history preserved.
[*]VPPAdminTools slash commands preserved.
[*]No Community Framework dependency.
[*]No Dabs Framework dependency.
[/list]

[h2]Current status[/h2]

Version 0.2.0-alpha.

Local client-to-server-to-client Global Chat validation has passed.
Vicinity, reconnect reset, input remapping, cooldown and logging tests have passed.
Hosted two-player validation has passed between players positioned in the north and south of Chernarus.
Bidirectional delivery, correct player names, independent cooldowns and one copy per recipient were confirmed.
Separate GLOBAL and VICINITY Discord webhook channels have been validated locally.

[h2]Source code[/h2]

[url=https://github.com/Zellno/ZellnoGlobalChat]
GitHub — ZellnoGlobalChat
[/url]

[h2]Monetization Permission[/h2]

Zellno permits the use of Zellno Global Chat on monetized DayZ servers,
provided that the server operator is registered, approved and listed under
Bohemia Interactive's DayZ Server Monetization program and complies with
all applicable rules.

This permission applies only to the original content provided by Zellno in
Zellno Global Chat. It does not grant permission to monetize DayZ itself or
any third-party modification or content used alongside this mod.

[url=https://www.bohemia.net/monetization]
Official monetization rules
[/url]

[url=https://www.bohemia.net/monetization/approved/dayz]
Approved DayZ servers
[/url]

[h2]Support the project[/h2]

Zellno mods are free and open source, but developing, testing and maintaining them takes time.

If you enjoy my work and would like to support future development, you can buy me a coffee here:

[url=https://www.buymeacoffee.com/noobopensource]
Buy Me a Coffee — Noob Open Source
[/url]

Thank you for your support!

[h2]License[/h2]

MIT License.

Developed and tested on Linux using the Windows DayZ Tools through Wine.
