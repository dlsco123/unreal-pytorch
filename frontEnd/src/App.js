import React, { useEffect, useState } from 'react';
import axios from 'axios';

function App() {
  const [data, setData] = useState(null);

  useEffect(() => {
    axios.get('http://localhost:8000/items/1')
      .then((response) => {
        setData(response.data);
      });
  }, []);

  return (
    <div className="App">
      {data && <div>Item id: {data.item_id}, q: {data.q}</div>}
    </div>
  );
}

export default App;