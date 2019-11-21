# Databases

This folder contains a module to populate and interact with a database
of smoke data provided in smoke.txt. 

To get started: 

* Make sure NodeJS 10.16.3
* `npm install`

Then to create the database, run `node database.js`. This will create a
folder `smoke.db` where database files will be stored.

To use, in a node shell:

```
const db = require("./database");
db.records.find({ID: 1}).toArray(function (err, data) { console.log(data); });
```

