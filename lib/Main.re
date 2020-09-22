open Cohttp;
open Cohttp_lwt_unix;

let url = "http://google.com/";

let request = {
  let%lwt (_resp, body) = Client.get(Uri.of_string(url));
  let%lwt body = body |> Cohttp_lwt.Body.to_string;
  Lwt.return(Some(body));
};

let timeout = {
  let%lwt () = Lwt_unix.sleep(5.);
  Lwt.return(None);
};

let run = () => {
  switch (Lwt_main.run(Lwt.pick([request, timeout]))) {
  | Some(response) => print_string(response)
  | None =>
    prerr_endline("Request timed out");
    exit(1);
  };
};
