# Zellno Global Chat

Independent open source DayZ mod that adds server-wide Global Chat while preserving vanilla Vicinity Chat.

## Status

Version 0.1.0-alpha. Local and single-client multiplayer validation is complete; online two-player validation remains pending.

## Usage

- Enter opens the vanilla chat input.
- Vicinity is selected by default. Vicinity means nearby players only.
- Numpad 4 alternates VICINITY and GLOBAL while chat is open.
- Numpad 4 is the default binding and can be remapped in the DayZ controls.
- Enter sends through the selected channel.

## Security

The server validates identity, target, content length, control characters and per-player cooldown before broadcasting.

## Configuration

Server file: $profile:ZellnoGlobalChat/settings.json
Defaults: enabled, 256 characters, 2000 ms cooldown, accepted/rejected logging.

## Compatibility

Messages beginning with ! or / remain available to ZenModCore and VPPAdminTools.

## Dependencies

Vanilla DayZ only. CF and Dabs Framework are not required.

## License

MIT. See LICENSE.
