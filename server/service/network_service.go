package service

import (
	"encoding/json"
	"log"
	"net"
	"net/http"

	"github.com/gorilla/mux"
)

type NetworkService struct {
}

var networkService *NetworkService = &NetworkService{}

type CIDR struct {
	Ip     net.IP
	IpMask net.IP
}

func (service *NetworkService) register(router *mux.Router) {
	router.HandleFunc("/get-network-info", func(w http.ResponseWriter, r *http.Request) {
		json.NewEncoder(w).Encode(service.getNetworkInfo())
	})
}

func (service *NetworkService) getNetworkInfo() []CIDR {
	netInterface, err := net.InterfaceByName("eth0")
	if err != nil {
		log.Printf("get-network-info: %v\n", err)
	}

	addrs, err := netInterface.Addrs()
	if err != nil {
		log.Printf("get-network-info: %v\n", err)
	}

	cidrs := make([]CIDR, 0)
	for _, addr := range addrs {
		ip, subnet, err := net.ParseCIDR(addr.String())
		if err != nil {
			log.Printf("get-network-info: %v\n", err)
		}
		cidrs = append(cidrs, CIDR{Ip: ip, IpMask: net.IP(subnet.Mask)})
	}
	return cidrs
}

func init() {
	services = append(services, networkService)
}
