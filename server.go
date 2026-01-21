package main

import (
	"fmt"
	"net/http"
	"os"
)

func main() {
	fServer := http.FileServer(http.Dir("./static"))
	http.Handle("/", disableCache(fServer))

	fmt.Println("go see http://127.0.0.1:3001")
	err := http.ListenAndServe(":3001", nil)
	if err != nil {
		fmt.Fprintln(os.Stderr, err)
	}
}

// disbling cache for development
func disableCache(next http.Handler) http.Handler {
	return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Cache-Control", "no-cache")
		next.ServeHTTP(w, r)
	})
}
