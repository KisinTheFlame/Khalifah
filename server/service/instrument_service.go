package service

import (
	"encoding/binary"
	"fmt"
	"log"
	"net"
	"net/http"

	"github.com/gorilla/mux"
)

type InstrumentService struct {
}

var instrumentService *InstrumentService = &InstrumentService{}

func (service *InstrumentService) register(router *mux.Router) {
	router = router.PathPrefix("/instrument").Subrouter()

	router.Methods("POST").Path("/get-serial").HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		conn, err := net.Dial("tcp", "172.19.0.1:3000")
		if err != nil {
			log.Printf("get-serial: %v\n", err)
		}
		defer conn.Close()
		prefix := receiveString(conn)
		major := receiveUint32(conn)
		minor := receiveUint32(conn)
		build := receiveUint32(conn)
		fmt.Fprintf(w, "%v.%v.%v.%v\n", prefix, major, minor, build)
	})
}

func init() {
	services = append(services, instrumentService)
}

func receiveUint32(conn net.Conn) uint32 {
	var x uint32
	binary.Read(conn, binary.LittleEndian, &x)
	return x
}

func receiveString(conn net.Conn) string {
	len := int(receiveUint32(conn))
	buffer := make([]byte, len)
	conn.Read(buffer)
	return string(buffer)
}
