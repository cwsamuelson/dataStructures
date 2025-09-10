Not precisely 'json', as in I'm not so sure I'm interested in handling parsing
JSON right away, but more like a structured any.  Essentially much like
`nlohmann::json`, except its parsing part.  Plausibly, I'd like to add
infrastructure to ease neatly generating structured parse/data trees.  Except
this could come from a `json`, `xml`, or otherwise arbitrary data document.