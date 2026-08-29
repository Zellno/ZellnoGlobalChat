# Zellno Global Chat testing

## Local validation — 2026-08-29

### Build and startup

- [x] PBO builds with prefix ZellnoGlobalChat.
- [x] Zellno signature validates.
- [x] Build performs no installation.
- [x] Dedicated server has no ZGC script compile errors.
- [x] Client has no ZGC script compile errors.
- [x] Server creates profiles/ZellnoGlobalChat/settings.json.
- [x] Server initializes the native RPC handler.

### Interface

- [x] Enter opens chat normally.
- [x] Initial channel is VICINITY.
- [x] Numpad 4 alternates VICINITY and GLOBAL.
- [x] Numpad 4 does not remain in the input when bound to the toggle action.
- [x] The toggle action respects control remapping.
- [x] Indicator does not cover the input field.
- [x] Reconnect resets the channel to VICINITY.

### Local multiplayer flow

- [x] VICINITY delegates to the vanilla chat flow.
- [x] GLOBAL travels from client to server and back to the sender.
- [x] Sender receives one server-relayed copy.
- [x] Global messages are not duplicated.
- [x] Server obtains the displayed player name from PlayerIdentity.
- [x] Cooldown rejects a rapid Global request server-side.
- [x] Accepted and rejected requests appear in server logs.

### Pending local validation

- [x] Messages beginning with ! bypass Global Chat and return to the existing chat chain.
- [ ] ZenModCore admin command execution with EnableCommands enabled.
- [x] VPPAdminTools / commands are consumed and do not enter Global Chat.
- [x] ZenModCore Up Arrow chat history still works.
- [x] Empty vanilla chat input does not reach the Global RPC.
- [ ] An empty payload from a modified client is rejected server-side.
- [x] Vanilla chat input truncates oversized pasted Global text before the RPC (35 characters observed locally).
- [ ] An oversized payload from a modified client is rejected server-side.
- [ ] Control-character Global messages are rejected.

## Pending online validation

- [ ] Two distant players connect simultaneously.
- [ ] VICINITY from player A does not reach distant player B.
- [ ] GLOBAL from player A reaches distant player B.
- [ ] Both players receive exactly one Global copy.
- [ ] Cooldown for player A does not affect player B.
- [ ] Both player names are displayed correctly.
