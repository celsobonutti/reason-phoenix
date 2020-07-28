type example = {username: string};

let socket =
  Socket.make(
    "/socket",
    Some(Socket.options(~transport="test", ~params={username: "test"}, ())),
  );

let _ = Socket.onOpen(socket, () => {Js.log("It works!")});

let _ =
  Socket.onClose(
    socket,
    () => {
      Js.log("Test");
    },
  );

Socket.connect(socket);

let channel = socket |> Channel.make("test", Js.Obj.empty());

channel
->Channel.join(~timeout=1000, ())
->Push.receive(~status="ok", ~callback=params => {Js.log(params)})
->Push.receive(~status="error", ~callback=params => {Js.log(params)});

channel->Channel.push(~event="test", ~payload=Js.Obj.empty(), ());

channel->Channel.leave();

module PresenceObject = {
  type t = {
    phx_ref: string,
    id: int,
    name: string,
  };
};

module PresenceMod = Presence.MakeModule(PresenceObject);

let presence = PresenceMod.make(channel, None);

open PresenceMod;

presence->onLeave((~id, ~currentPresence, ~newPresence) => {
  Js.log(id);
  switch (unwrap(currentPresence), unwrap(newPresence)) {
  | (None, None) => Js.log("No presences!")
  | (None, Some({id: userId, phx_ref: _})) =>
    Js.log({j|New user: $userId|j})
  | (Some({id: userId, phx_ref}), Some(_)) =>
    Js.log({j| User $userId logged from a new device: $phx_ref"|j})
  | _ => Js.log("Something ins very, very wrong around here.")
  };
});
