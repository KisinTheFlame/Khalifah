package service

import (
	"net/http"

	"github.com/KisinTheFlame/khalifah/server/model/dto"
	"github.com/KisinTheFlame/khalifah/server/utils/jsonutils"
	"github.com/gorilla/mux"
)

type UserService struct{}

var userService *UserService = &UserService{}

func (service *UserService) register(router *mux.Router) {
	router = router.PathPrefix("/user").Subrouter()

	router.Methods("POST").Path("/register").HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		request := jsonutils.GetJsonBody[dto.UserRegister](r)
		service.registerUser(request)
	})
	router.Methods("POST").Path("/login").HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		request := jsonutils.GetJsonBody[dto.UserLogin](r)
		service.loginUser(w, request)
	})
}

func (service *UserService) registerUser(request *dto.UserRegister) {

}

func (service *UserService) loginUser(w http.ResponseWriter, request *dto.UserLogin) {
}

func (service *UserService) changePassword() {
}

func init() {
	services = append(services, userService)
}
