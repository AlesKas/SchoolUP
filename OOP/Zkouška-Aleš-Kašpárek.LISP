#|
Dokumentace
Ke správnému fungování je potřeba mít načtenou knihovnu Micro-graphics a soubory 08.lisp.

Třída Switchable-shape
Třída uchovává více prvků, avšak vždy vykreslí pouze jeden. Aktivní obrazec je uchováván ve vlastnosti acive-item a může se k
němu přistupovat přes vlastnost active-item-index. Třída dědí z třídy compound-shape, tím pádem nemusí obsahovat vlastnost items. 

Vlastnosti
active-item - slouží k uchování vykreslovaného obrazce, vlastnost pouze ke čtení
active-item-index - slouží k uchování indexu vykreslovaného obrazce, vlastnost ke čtení i zápisu

Zprávy
next-item - zvýší vlastnost active-item-index o 1
previous-item - sníží vlastnost active-item-index o 1

Upravené metody
set-mg-params
draw
set-items

TO DO:
základní implementace - hotovo
posouvání objektů z listeneru - hotovo
implementace obshluhy klikání
|#

(defclass switchable-shape (compound-shape)
  ((active-item-index :initform nil)))

(defmethod do-set-active-item-index ((sw switchable-shape) num)
  (unless (typep num 'number)
    (error "New index should be number"))
  (setf (slot-value sw 'active-item-index) num))

(defmethod set-active-item-index ((sw switchable-shape) num)
  (send-with-change sw 'do-set-active-item-index
                    'set-active-item-index `(,num)))

(defmethod active-item-index ((sw switchable-shape))
  (slot-value sw 'active-item-index))

(defmethod active-item ((sw switchable-shape))
  (if (and (active-item-index sw) (> (length (items sw)) (active-item-index sw)))
      (nth (active-item-index sw) (items sw))
    nil))

;;;Úprava a implementace abstraktních metod

(defmethod set-mg-params ((sw switchable-shape))
  (call-next-method)
  (mg:set-param (shape-mg-window sw)
                :filledp 
                (filledp (active-item sw))))

(defmethod draw ((sw switchable-shape))
  (do-draw-sw sw)
  (call-next-method))

(defmethod do-draw-sw ((sw switchable-shape))
  (when (active-item sw)
    (set-mg-params sw)
    (do-draw (active-item sw))))

(defmethod check-items ((sw switchable-shape) item)
  sw)

(defmethod set-items ((sw switchable-shape) items)
  (call-next-method))

;;;Nove metody

(defmethod set-window ((sw switchable-shape) win)
  (setf (slot-value sw 'window) win)
  (dolist (item (items sw))
    (setf (slot-value item 'window) win))
  sw)

(defmethod check-active-item-index ((sw switchable-shape))
  (unless (active-item-index sw)
    (set-active-item-index sw 0)))

(defmethod next-item ((sw switchable-shape))
  (check-active-item-index sw)
  (set-active-item-index sw (if (= (length (items sw)) (+ 1 (active-item-index sw)))
                                0
                              (+ 1 (active-item-index sw)))))

(defmethod previous-item ((sw switchable-shape))
  (check-active-item-index sw)
  (set-active-item-index sw (if (= (length (items sw)) (+ 1 (active-item-index sw)))
                                0
                              (+ 1 (active-item-index sw)))))
  
  


;;;Obsluha klikání



(defmethod initialize-instance ((sw switchable-shape) &key)
  (call-next-method)
  (set-active-item-index sw 0))