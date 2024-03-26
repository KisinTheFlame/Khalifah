package po

import "github.com/KisinTheFlame/khalifah/server/model/bo"

type User struct {
	Id           int
	Username     string
	Password     string
	PasswordSalt string
}

func (user *User) ToBO() *bo.User {
	return &bo.User{
		Username:     user.Username,
		Password:     user.Password,
		PasswordSalt: user.PasswordSalt,
	}
}
