package main

import (
	"context"
	"log"
	"net/http"
	"os"
	"os/signal"

	"github.com/KisinTheFlame/khalifah/server/service"
	"github.com/gorilla/mux"
)

func main() {
	router := mux.NewRouter()

	service.RegisterService(router.PathPrefix("/api").Subrouter())

	router.PathPrefix("/").Handler(http.FileServer(http.Dir("./webroot")))

	systemInterrupt := make(chan os.Signal, 1)
	signal.Notify(systemInterrupt, os.Interrupt)

	server := &http.Server{Addr: ":8080", Handler: router}
	go func() {
		if err := server.ListenAndServe(); err != nil {
			log.Printf("ListenAndServe: %v\n", err)
		}
	}()

	<-systemInterrupt
	if err := server.Shutdown(context.TODO()); err != nil {
		log.Fatalf("Shutdown: %v\n", err)
	}
	log.Println("Shutdown.")
}
