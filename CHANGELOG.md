# Changelog

## 0.2.0-alpha

- Added optional Discord webhook forwarding.
- Added separate webhook configuration for GLOBAL and VICINITY.
- Added server-validated, client-reported VICINITY audit records with the `[ZGC] vicinity-audit` identifier.
- Added an independent per-player rate limit for VICINITY audit requests.
- Preserved the existing `[ZGC] accepted` identifier for GLOBAL messages.
- Added configurable Discord webhook username.
- Restricted webhook URLs to the official Discord webhook endpoint.
- Disabled Discord allowed mentions in forwarded messages.
- Added Discord-safe message sanitization without changing in-game or server-log content.
- Added the World script module required by the Discord REST transport.
- Validated separate GLOBAL and VICINITY Discord channels locally.
- Removed temporary Discord payload and callback diagnostics.

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
