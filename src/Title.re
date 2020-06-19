module Styles = {
  let input =
    ReactDOMRe.Style.make(
      ~width="100%",
      ~border="none",
      ~textAlign="center",
      ~fontSize="32px",
      ~fontWeight="500",
      ~outline="none",
      ~padding="20px 0",
      (),
    );
};

[@react.component]
let make = () => {
  let (title, setTitle) = React.useState(() => "New List");
  <input
    style=Styles.input
    placeholder="List Title"
    value=title
    onChange={event => {
      let value = ReactEvent.Form.target(event)##value;
      setTitle(_ => value);
    }}
  />;
};