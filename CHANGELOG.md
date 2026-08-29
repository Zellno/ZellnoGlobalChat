# Changelog

## 0.1.0-alpha

- Added server-wide player Global Chat.
- Preserved vanilla Vicinity Chat behavior.
- Added a clear VICINITY/GLOBAL channel indicator.
- Added a configurable channel-toggle input with Numpad 4 as default.
- Added server-authoritative player names.
- Added sender/target identity validation for Global RPC requests.
- Added empty-message, length and control-character validation.
- Added configurable per-player Global Chat cooldown.
- Added accepted and rejected request logging.
- Added JSON configuration under the server profile.
- Preserved VPPAdminTools slash-command handling.
- Preserved ZenModCore Up Arrow chat history.
- Completed local client-to-server-to-client Global Chat validation.
- Completed local Vicinity, reconnect, remapping and cooldown tests.
- Completed hosted two-player validation between the north and south of Chernarus.
- Confirmed bidirectional Global Chat, correct player names and one copy per recipient.
- Confirmed that per-player cooldowns remain independent.
