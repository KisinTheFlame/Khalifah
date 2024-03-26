package repository

import (
	"database/sql"
	"log"

	_ "github.com/mattn/go-sqlite3"
)

var db *sql.DB

func init() {
	var err error
	db, err = sql.Open("sqlite3", "data.db")
	if err != nil {
		log.Fatalf("repository init: %v", err)
	}
}
