This workshop is about a bracket check function.

This is implemented using stacks.

This is the following way bracketCheck() function checks for the correct match of brackets.

| Sample string | return value |
|---|---|
|a(b)c[d]ef|true|
|aa[bcd(efg{hij}k[lm]no)p]qrs|true|
|a(b)c]d|false|
|[[]|false|
|aa(bb{cc)dd}ee|false|
