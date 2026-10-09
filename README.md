# Zellno Global Chat

Independent open source DayZ mod that adds server-wide Global Chat while preserving vanilla Vicinity Chat.

## Status

Version 0.2.0-alpha. Local and hosted two-player multiplayer validation is complete. Optional Discord webhook logging for GLOBAL and VICINITY has also been validated locally.

## Usage

- Enter opens the vanilla chat input.
- Vicinity is selected by default. Vicinity means nearby players only.
- Numpad 4 alternates VICINITY and GLOBAL while chat is open.
- Numpad 4 is the default binding and can be remapped in the DayZ controls.
- Enter sends through the selected channel.

## Security

The server validates identity, target, content length, control characters and per-player cooldown before broadcasting.

GLOBAL and VICINITY Discord payloads disable allowed mentions. Webhook URLs are accepted only from the official Discord webhook endpoint. VICINITY audit requests have an independent server-side rate limit.

## Logging and Discord

GLOBAL messages retain the `[ZGC] accepted` server-log identifier.

VICINITY remains vanilla gameplay chat, but the client reports a server-validated audit record using the `[ZGC] vicinity-audit` identifier. Identity, target and content are validated server-side; the record is still client-reported because vanilla VICINITY delivery uses the original DayZ chat flow.

GLOBAL and VICINITY can optionally be forwarded to separate Discord webhook channels.

## Configuration

Server file: `$profile:ZellnoGlobalChat/settings.json`

Defaults:

- Global Chat enabled.
- Maximum server-side message length: 256 characters.
- Per-player Global Chat cooldown: 2000 milliseconds.
- Per-player VICINITY audit cooldown: 500 milliseconds.
- Accepted and rejected request logging enabled.
- Discord GLOBAL webhook disabled until a URL is configured.
- Discord VICINITY webhook disabled until a URL is configured.
- Discord webhook username: `Zellno Global Chat`.

Discord settings:

- `VicinityAuditCooldownMilliseconds`
- `DiscordGlobalWebhookUrl`
- `DiscordVicinityWebhookUrl`
- `DiscordWebhookUsername`

Webhook URLs remain in the server profile and are not embedded in the mod package.

## Compatibility

Messages beginning with ! or / remain available to ZenModCore and VPPAdminTools.

## Dependencies

Vanilla DayZ only. CF and Dabs Framework are not required.

## License

MIT. See LICENSE.

## Steam Workshop

https://steamcommunity.com/sharedfiles/filedetails/?id=3792361356
