#lang racket

;; Read a set of numbers from input, and convert them 
;; to their respective unicode character
(printf (list->string 
 (map (compose integer->char string->number) 
      (string-split (read-line))))) 


