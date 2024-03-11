package service

import (
	"database/sql"
	"fmt"
	"log"
	"net/http"

	"github.com/gorilla/mux"
	_ "github.com/mattn/go-sqlite3"
)

type UserService struct {
}

var userService *UserService = &UserService{}

func (service *UserService) register(router *mux.Router) {
	router.HandleFunc("/sqltest", func(w http.ResponseWriter, r *http.Request) {
		fmt.Fprintln(w, service.sqlTest())
	})
}

func (service *UserService) sqlTest() string {
	db, err := sql.Open("sqlite3", "data.db")
	if err != nil {
		log.Printf("init: %v\n", err)
	}
	defer db.Close()
	var version string
	if err := db.QueryRow("SELECT SQLITE_VERSION()").Scan(&version); err != nil {
		log.Printf("init: %v\n", err)
	}
	return version
}

func (service *UserService) registerUser() {

}

func (service *UserService) loginUser() {

}

func (service *UserService) changePassword() {

}

func init() {
	services = append(services, userService)
}
