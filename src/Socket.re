type t;

[@bs.deriving abstract]
type options('a) = {
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
  binaryType: string,
  params: 'a
};

[@bs.module "phoenix"]
[@bs.new]
external make : string => option(options('a)) => t = "Socket";

[@bs.send] external endPointURL : t => string = "endPointURL";
[@bs.send] external protocol : t => string = "protocol";
[@bs.send] external connect : t => unit = "connect";
[@bs.send] external hasLogger : t => bool = "hasLogger";
[@bs.set] external onOpen : (t, unit => unit) => unit = "onOpen";
[@bs.set] external onClose : (t, Js.t('a) => unit) => unit = "onClose";
[@bs.set] external onError : (t, Js.t('a) => unit) => unit = "onError";
[@bs.set] external onMessage : (t, Js.t('a) => unit) => unit = "onMessage";