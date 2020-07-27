type t('a);

type presence('a) = {metas: array('a)};

type presences('a) = Belt.Map.String.t(presence('a));

type diff('a) = {
  joins: presences('a),
  leaves: presences('a),
};

type presenceEventArgs('a) = {
  key: option(string),
  currentPresence: option(Js.t('a)),
  newPresence: option(Js.t('a)),
};

type presenceCallback('a) =
  (~id: string, ~currentPresence: presence('a), ~newPresence: presence('a)) =>
  unit;

type presenceOpts = {
  state: string,
  diff: string,
};

[@bs.module "phoenix"] [@bs.new]
external make:
  ([@bs.ignore] 'a, Channel.t, ~options: presenceOpts=?, unit) => t('a) =
  "Presence";

[@bs.module "phoenix"] [@bs.scope "Presence"]
external syncDiff:
  (
    [@bs.ignore] t('a),
    ~currentState: presences('a),
    ~diff: diff('a),
    ~onJoin: presenceCallback('a)=?,
    ~onLeave: presenceCallback('a)=?,
    unit
  ) =>
  presences('a) =
  "syncDiff";

[@bs.module "phoenix"] [@bs.scope "Presence"]
external syncState:
  (
    [@bs.ignore] t('a),
    ~currentState: presences('a),
    ~newState: presences('a),
    ~onJoin: presenceCallback('a)=?,
    ~onLeave: presenceCallback('a)=?,
    unit
  ) =>
  presences('a) =
  "syncState";

[@bs.set]
external onLeave: (t('a), presenceCallback('a)) => unit = "onLeave";
[@bs.set] external onJoin: (t('a), presenceCallback('a)) => unit = "onJoin";

//TO-DO: Add Presence.list