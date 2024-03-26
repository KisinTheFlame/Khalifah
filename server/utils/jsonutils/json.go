package jsonutils

import (
	"encoding/json"
	"net/http"
)

func GetJsonBody[T any](r *http.Request) *T {
	var t T
	json.NewDecoder(r.Body).Decode(&t)
	return &t
}
