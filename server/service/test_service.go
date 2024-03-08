package service

import (
	"fmt"
	"net/http"

	"github.com/gorilla/mux"
)

type TestService struct {
	times int
}

var testService *TestService = &TestService{times: 0}

func (service *TestService) register(router *mux.Router) {
	router.HandleFunc("/test", func(w http.ResponseWriter, r *http.Request) {
		service.times++
		fmt.Fprintf(w, "you have visited for %v times!\n", service.times)
	})
}

func init() {
	services = append(services, testService)
}
