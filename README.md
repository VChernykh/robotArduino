# robotArduino

Основная информация <a href ="https://habr.com/post/381775/"> здесь</a> и <a http://wiki.amperka.ru/робототехника:робот-с-датчиками-линии-на-arduino> здесь</a>
<p>Необходимо использовать алгоритмы обратной связи - напряжение на моторах будет зависеть от расстояния до стены, в свою очередь вращение моторов изменяет расстояние до стены.</p>
<p>Также возникают следующие проблемы:</p>
<ul>
<li>Датчики не идеальны, могут "шуметь" и временно давать сбойный сигнал.</li>
<li>Алгоритм должен быть умным. Если мы достаточно далеко от стены, можно повернуть лишь немного. Если приблизились уже вплотную, то разворот нужно сделать крутым.</li>
</ul>
<p>Для этого разработаны следующие алгоритмы:</p>
<ul>
<li>Алгоритмы фильтрации значений, в частности фильтр Калмана. Правильно подобранный фильтр "убирает" из показаний датчиков лишний "шум" и некорректные значения.</li>
<li>Алгоритм ПИД - регуляции. Позволяет рассчитать значение управляющего воздействия (Напряжения на моторе робота) от сигнала (расстояния от стены). Состоит из трех компонент: Пропорциональной (сигнал рассогласования), интеграла сигнала рассогласования, производной сигнала рассогласования.</li>
</ul>
