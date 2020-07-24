type t;

[@bs.module "phoenix"]
[@bs.new]
external make : string => Js.t('a) => Socket.t => t = "Channel";

[@bs.send]
external push : t => string => Js.t('a) => option(int) => unit = "push";