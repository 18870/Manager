# Manager
A simple cli data manager written in c++.  

# Compile
**Need at least C++11.**
## Dev-C++
Add argument `-static-libgcc -std=c++11 -std=gnu++11` to complier option.

# Generate new manager
```json
"Student Info":{
    "Datas":[
        {"key": "ID", "type": "string"},
        {"key": "name", "type": "string"},
        {"key": "sex", "type": "string"},
        {"key": "birth", "type": "string"},
        {"key": "chinese", "type": "double"},
        {"key": "math", "type": "double"},
        {"key": "english", "type": "double"},
        {"key": "science", "type": "double"},
        {"key": "pe", "type": "double"}
    ],
    "Searchable keys":[
        "name",
        "ID"
    ],
    "Display keys": [
        "name",
        "ID"
    ]
}
```
Use `json` like this to generate new manager. Add it into [system.json](/data/system.json), create an object like `Manager("Student Info")` and call `manager.panel()` function.  
`Datas` list contains a list of data to be stored with its type.  
All supported types:
- string
- double
- int
- bool

`Searchable keys` list contains a list of keyname that use to search when call `manager.search()` function.  
`Display keys` list contains a list of keyname that use to show brief introduction in `manager.display()` function.  

All keys are in order.

# Multi language
See [lang.json](/data/lang.json).

# License
This work is licensed under the [MIT License](LICENSE).