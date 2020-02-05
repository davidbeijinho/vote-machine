import React from "react";

function Button({ children, onClick, ...other }) {
  return (
    <button className="button" onClick={onClick} {...other}>
      {children}
    </button>
  );
}

export default Button;
