type t;

type presence;

type presences = Belt.Map.String.t(presence);

type diff = {
  joins: presences,
  leaves: presences,
};

type presenceEventArgs('a) = {
  key: option(string),
  currentPresence: option(Js.t('a)),
  newPresence: option(Js.t('a)),
};

type presenceCallback =
  (~id: string, ~currentPres: presence, ~newPresence: presence) => unit;

[@bs.module "phoenix"] [@bs.new] external make: Channel.t => t = "Presence";

[@bs.set] external onLeave: (t, option(string) => unit) => unit = "onLeave";

// [@bs.module "phoenix"] [@bs.scope "Presence"]
// external syncDiff:
//   (
//     presences,
//     diff,
//     option(presenceEvent('c)),
//     option(presenceEvent('d))
//   ) =>
//   presences =
//   "syncDiff";
