package repository

import (
	"github.com/KisinTheFlame/khalifah/server/model/bo"
	"github.com/KisinTheFlame/khalifah/server/model/po"
)

func GetUserByUserName(username string) *bo.User {
	const QUERY = "SELECT id, username, password, password_salt FROM user WHERE username = ?"
	var user po.User
	if err := db.QueryRow(QUERY, username).Scan(&user.Id, &user.Username, &user.Password, &user.PasswordSalt); err != nil {
		return nil
	}
	return user.ToBO()
}
