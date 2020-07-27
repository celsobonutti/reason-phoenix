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
    test => {
      let a = test##testing;
      Js.log(a);
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

type presenceType = {
  phx_ref: string,
  id: string,
};

//TO-DO: Pass type instead of example (if possible)
let presence = Presence.make({phx_ref: "", id: ""}, channel, ());

presence->
Presence.onLeave((~id, ~currentPresence, ~newPresence) => {
  Js.log(id);
  Js.log(currentPresence);
  Js.log(newPresence);
});
