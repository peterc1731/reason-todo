module Styles = {
  let container =
    ReactDOMRe.Style.make(
      ~width="100%",
      ~height="30px",
      ~display="flex",
      ~alignItems="center",
      ~borderRadius="3px",
      ~padding="5px 10px",
      (),
    );
  let input =
    ReactDOMRe.Style.make(
      ~flex="1",
      ~border="none",
      ~textAlign="left",
      ~fontSize="14px",
      ~fontWeight="400",
      ~outline="none",
      ~backgroundColor="transparent",
      (),
    );
  let checkBox =
    ReactDOMRe.Style.make(
      ~display="flex",
      ~alignItems="center",
      ~justifyContent="center",
      ~border="1px solid black",
      ~borderRadius="3px",
      ~width="20px",
      ~height="20px",
      ~marginRight="10px",
      ~cursor="pointer",
      (),
    );
  let deleteBtn =
    ReactDOMRe.Style.make(
      ~display="flex",
      ~alignItems="center",
      ~justifyContent="center",
      ~width="20px",
      ~height="20px",
      ~marginLeft="10px",
      ~cursor="pointer",
      (),
    );
};

[@react.component]
let make =
    (
      ~item: Todo.item,
      ~updateItem: Todo.item => unit,
      ~deleteItem: unit => unit,
    ) => {
  let (hovered, setHovered) = React.useState(() => false);
  let filled = item.text !== "";
  let completed = item.complete;
  let containerStyle =
    ReactDOMRe.Style.combine(
      Styles.container,
      ReactDOMRe.Style.make(
        ~backgroundColor=hovered ? "#e8e8e8" : "transparent",
        (),
      ),
    );
  let inputStyle =
    ReactDOMRe.Style.combine(
      Styles.input,
      ReactDOMRe.Style.make(
        ~textDecoration=completed ? "strikethrough" : "none",
        (),
      ),
    );

  <div
    style=containerStyle
    onMouseEnter={_ => setHovered(_ => true)}
    onMouseLeave={_ => setHovered(_ => false)}>
    <div
      style=Styles.checkBox
      onClick={_ => updateItem({...item, complete: !item.complete})}>
      {switch (completed, filled) {
       | (true, true) => <div> {React.string({j|✓|j})} </div>
       | (_, false) => <div> {React.string({j|+|j})} </div>
       | _ => ReasonReact.null
       }}
    </div>
    <input
      style=inputStyle
      placeholder="List Item"
      value={item.text}
      onChange={event => {
        let value = ReactEvent.Form.target(event)##value;
        updateItem({...item, text: value});
      }}
    />
    {hovered && filled
       ? <div style=Styles.deleteBtn onClick={_ => deleteItem()}>
           <div> {React.string({j|╳|j})} </div>
         </div>
       : ReasonReact.null}
  </div>;
};