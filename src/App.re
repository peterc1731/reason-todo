let initialItems: array(Todo.item) = [|{text: "", complete: false, id: 0}|];

module Styles = {
  let container =
    ReactDOMRe.Style.make(
      ~display="flex",
      ~flexDirection="column",
      ~alignItems="center",
      ~width="400px",
      (),
    );
  let list =
    ReactDOMRe.Style.make(
      ~display="flex",
      ~flexDirection="column",
      ~width="100%",
      (),
    );
};

[@react.component]
let make = () => {
  let (items, setItems) = React.useState(() => initialItems);

  let updateItem = (index: int, item: Todo.item) => {
    setItems(oldItems => {
      let newItems = Array.copy(oldItems);
      newItems[index] = item;

      if (!newItems->Belt.Array.some(x => x.text == "")) {
        Array.concat([newItems, initialItems]);
      } else {
        newItems;
      };
    });
  };

  let deleteItem = (index: int, ()) =>
    setItems(oldItems => {
      oldItems->Belt.Array.keepWithIndex((_, i) => i !== index)
    });

  <div style=Styles.container>
    <Title />
    <div style=Styles.list>
      {items
       ->Belt.Array.mapWithIndex((i, item) =>
           <ListItem
             item
             deleteItem={deleteItem(i)}
             updateItem={updateItem(i)}
             key={j|$item.id|j}
           />
         )
       ->React.array}
    </div>
  </div>;
};