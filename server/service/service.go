package service

import "github.com/gorilla/mux"

var services []Service = make([]Service, 0)

type Service interface {
	register(router *mux.Router)
}

func RegisterService(router *mux.Router) {
	for _, service := range services {
		service.register(router)
	}
}
