import React from "react";
import { useLocalStorage } from "react-use";
import ReactDOM from "react-dom";

import Button from "./components/Button";
import Icon from "./components/Icon";
import Thanks from "./components/Thanks";

const happyVote = "🙂";
const normalVote = "😐";
const sadVote = "🙁";

function App() {
  const [vote, setVote] = useLocalStorage("vote", null);

  const sendVote = (url, vote) => () => {
    fetch(`/vote/${url}`, { method: "POST" })
      .then(res => res.json())
      .then(() => {
        setVote(vote);
      })
      .catch(console.error);
  };

  return (
    <>
      {vote ? (
        <Thanks vote={vote} />
      ) : (
        <div className="container">
          <Button onClick={sendVote("green", happyVote)}>
            <Icon type={happyVote} />
          </Button>
          <Button onClick={sendVote("yellow", normalVote)}>
            <Icon type={normalVote} />
          </Button>
          <Button onClick={sendVote("red", sadVote)}>
            <Icon type={sadVote} />
          </Button>
        </div>
      )}
    </>
  );
}

ReactDOM.render(<App />, document.getElementById("app"));
