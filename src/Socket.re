type t;

type ref;

type messageArgs('a) = {
  event: string,
  join_ref: option(string),
  payload: 'a,
  ref: option(string),
  topic: string,
};

type protocol = /* [ | `wss | `ws] */ string; 

type binaryType = /* [ | `blob | `arraybuffer] */ string;

type logger('a) = (~kind: string, ~msg: string, ~data: 'a) => unit;

[@bs.deriving abstract]
type options('a, 'b) = {
  [@bs.optional]
  transport: string,
  [@bs.optional]
  timeout: int,
  [@bs.optional]
  heartbeatIntervalMs: int,
  [@bs.optional]
  reconnectAfterMs: int,
  [@bs.optional]
  rejoinAfterMs: int,
  [@bs.optional]
  longpollerTimeout: int,
  [@bs.optional]
  binaryType,
  [@bs.optional]
  logger: 'b,
  params: 'a,
};

[@bs.module "phoenix"] [@bs.new]
external make: (string, option(options(_, _))) => t = "Socket";

[@bs.send] external endPointURL: t => string = "endPointURL";
[@bs.send] external protocol: t => protocol = "protocol";
[@bs.send] external connect: t => unit = "connect";
[@bs.send]
external disconnect:
  (t, ~callback: 'a => unit, ~code: int=?, ~reason: string=?, unit) => unit =
  "disconnect";
[@bs.send]
external log: (t, ~kind: string, ~msg: string, ~param: 'a) => unit = "log";
[@bs.send] external hasLogger: t => bool = "hasLogger";
[@bs.send] external onOpen: (t, unit => unit) => ref = "onOpen";
[@bs.send] external onClose: (t, 'a => unit) => ref = "onClose";
[@bs.send] external onError: (t, 'a => unit) => ref = "onError";
[@bs.send]
external onMessage: (t, messageArgs('a) => unit) => ref = "onMessage";
[@bs.send] external connectionState: t => unit = "connectionState";
[@bs.send] external isConnected: t => unit = "isConnected";
[@bs.send] external makeRef: t => ref = "makeRef";
[@bs.send] external push: (t, messageArgs('a)) => unit = "push";
