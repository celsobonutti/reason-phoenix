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

let _ = Socket.connect(socket);

let channel = socket |> Channel.make("test", Js.Obj.empty());

channel ->
Channel.push("test", Js.Obj.empty(), None);