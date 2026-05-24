<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=yes">
    <title>Физика ходьбы: калькулятор энергозатрат</title>
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }

        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            min-height: 100vh;
            padding: 20px;
        }

        .container {
            max-width: 800px;
            margin: 0 auto;
        }

        .card {
            background: white;
            border-radius: 20px;
            box-shadow: 0 20px 40px rgba(0,0,0,0.1);
            overflow: hidden;
            margin-bottom: 20px;
        }

        .header {
            background: linear-gradient(135deg, #2c3e50, #1a2632);
            color: white;
            padding: 25px;
            text-align: center;
        }

        .header h1 {
            font-size: 1.8rem;
            margin-bottom: 10px;
        }

        .header p {
            opacity: 0.8;
            font-size: 0.95rem;
        }

        .content {
            padding: 25px;
        }

        .input-group {
            margin-bottom: 20px;
        }

        label {
            display: block;
            font-weight: 600;
            margin-bottom: 8px;
            color: #333;
        }

        input, select {
            width: 100%;
            padding: 12px 15px;
            border: 2px solid #e0e0e0;
            border-radius: 10px;
            font-size: 16px;
            transition: border-color 0.3s;
        }

        input:focus {
            outline: none;
            border-color: #667eea;
        }

        .row {
            display: flex;
            gap: 15px;
            flex-wrap: wrap;
        }

        .row .input-group {
            flex: 1;
            min-width: 120px;
        }

        .checkbox-group {
            display: flex;
            align-items: center;
            gap: 10px;
            margin: 15px 0;
        }

        .checkbox-group input {
            width: auto;
        }

        button {
            background: linear-gradient(135deg, #667eea, #764ba2);
            color: white;
            border: none;
            padding: 14px 30px;
            font-size: 18px;
            font-weight: 600;
            border-radius: 10px;
            cursor: pointer;
            width: 100%;
            transition: transform 0.2s, box-shadow 0.2s;
        }

        button:hover {
            transform: translateY(-2px);
            box-shadow: 0 10px 20px rgba(0,0,0,0.2);
        }

        .results {
            background: #f8f9fa;
            border-radius: 15px;
            padding: 20px;
            margin-top: 25px;
        }

        .results h3 {
            color: #333;
            margin-bottom: 15px;
            padding-bottom: 10px;
            border-bottom: 2px solid #667eea;
        }

        .result-item {
            display: flex;
            justify-content: space-between;
            padding: 12px 0;
            border-bottom: 1px solid #e0e0e0;
        }

        .result-item:last-child {
            border-bottom: none;
        }

        .result-label {
            font-weight: 600;
            color: #555;
        }

        .result-value {
            font-size: 1.2rem;
            font-weight: 700;
            color: #667eea;
        }

        .formula-note {
            background: #eef2ff;
            padding: 15px;
            border-radius: 10px;
            margin-top: 20px;
            font-size: 0.85rem;
            color: #333;
        }

        .formula-note h4 {
            margin-bottom: 10px;
            color: #667eea;
        }

        .formula-note p {
            margin: 5px 0;
        }

        .footer {
            text-align: center;
            padding: 15px;
            color: white;
            font-size: 0.8rem;
        }

        @media (max-width: 600px) {
            .header h1 {
                font-size: 1.4rem;
            }
            .result-value {
                font-size: 1rem;
            }
        }
    </style>
</head>
<body>
    <div class="container">
        <div class="card">
            <div class="header">
                <h1>🚶‍♂️ Физика ходьбы</h1>
                <p>Калькулятор энергозатрат при ходьбе на основе законов механики</p>
            </div>
            <div class="content">
                <div class="row">
                    <div class="input-group">
                        <label>⚖️ Ваш вес (кг)</label>
                        <input type="number" id="weight" value="70" step="1" placeholder="кг">
                    </div>
                    <div class="input-group">
                        <label>📏 Рост (см)</label>
                        <input type="number" id="height" value="170" step="1" placeholder="см">
                    </div>
                </div>

                <div class="checkbox-group">
                    <input type="checkbox" id="manualStepCheckbox">
                    <label for="manualStepCheckbox">Ввести длину шага вручную</label>
                </div>

                <div class="row" id="stepLengthRow" style="display: none;">
                    <div class="input-group">
                        <label>🚶 Длина шага (м)</label>
                        <input type="number" id="stepLengthManual" value="0.75" step="0.01" placeholder="м">
                    </div>
                </div>

                <div class="row">
                    <div class="input-group">
                        <label>👣 Количество шагов</label>
                        <input type="number" id="steps" value="1000" step="100" placeholder="шагов">
                    </div>
                    <div class="input-group">
                        <label>⏱️ Время ходьбы (мин)</label>
                        <input type="number" id="time" value="12" step="1" placeholder="минут">
                    </div>
                </div>

                <button onclick="calculate()">🔬 Рассчитать энергозатраты</button>

                <div class="results" id="results" style="display: none;">
                    <h3>📊 Результаты расчета</h3>
                    <div class="result-item">
                        <span class="result-label">👣 Длина шага:</span>
                        <span class="result-value" id="stepLengthResult">—</span>
                    </div>
                    <div class="result-item">
                        <span class="result-label">📏 Пройденное расстояние:</span>
                        <span class="result-value" id="distanceResult">—</span>
                    </div>
                    <div class="result-item">
                        <span class="result-label">⚡ Средняя скорость:</span>
                        <span class="result-value" id="speedResult">—</span>
                    </div>
                    <div class="result-item">
                        <span class="result-label">⚙️ Механическая работа:</span>
                        <span class="result-value" id="workResult">—</span>
                    </div>
                    <div class="result-item">
                        <span class="result-label">💪 Средняя мощность:</span>
                        <span class="result-value" id="powerResult">—</span>
                    </div>
                    <div class="result-item">
                        <span class="result-label">🔥 Сожжено калорий (ккал):</span>
                        <span class="result-value" id="caloriesResult">—</span>
                    </div>
                    <div class="formula-note">
                        <h4>📐 Как мы считаем</h4>
                        <p><strong>Длина шага (по росту):</strong> рост × 0,415 (формула эргономики)</p>
                        <p><strong>Работа против силы тяжести:</strong> A = m × g × h (h = 0,03 м — подъем центра масс)</p>
                        <p><strong>Механическая работа:</strong> A = m × g × h × количество шагов</p>
                        <p><strong>Мощность:</strong> P = A / t (t — время в секундах)</p>
                        <p><strong>Калории (с учетом КПД 25%):</strong> Q = A / 4184 / 0,25</p>
                        <p><strong>Используемые законы:</strong> II закон Ньютона, закон сохранения энергии, закон рычага</p>
                    </div>
                </div>
            </div>
        </div>
        <div class="footer">
            Индивидуальный проект по физике | Исследование биомеханики ходьбы
        </div>
    </div>

    <script>
        // Длина шага по росту (коэффициент 0.415 - среднее значение для взрослого человека)
        function getStepLengthFromHeight(heightCm) {
            return heightCm * 0.415 / 100;
        }

        function calculate() {
            // Получаем значения
            const weight = parseFloat(document.getElementById('weight').value);
            const height = parseFloat(document.getElementById('height').value);
            const steps = parseFloat(document.getElementById('steps').value);
            const timeMin = parseFloat(document.getElementById('time').value);
            
            // Определяем длину шага
            let stepLength;
            const manualCheckbox = document.getElementById('manualStepCheckbox');
            if (manualCheckbox.checked) {
                stepLength = parseFloat(document.getElementById('stepLengthManual').value);
            } else {
                stepLength = getStepLengthFromHeight(height);
            }
            
            // Проверка на корректность данных
            if (isNaN(weight) || weight <= 0) {
                alert('Пожалуйста, введите корректный вес');
                return;
            }
            if (isNaN(steps) || steps <= 0) {
                alert('Пожалуйста, введите количество шагов');
                return;
            }
            if (isNaN(timeMin) || timeMin <= 0) {
                alert('Пожалуйста, введите время');
                return;
            }
            if (isNaN(stepLength) || stepLength <= 0) {
                alert('Пожалуйста, введите корректную длину шага');
                return;
            }
            
            // Константы
            const g = 9.81;                    // ускорение свободного падения (м/с²)
            const h = 0.03;                    // вертикальное перемещение центра масс (м) — 3 см
            const efficiency = 0.25;           // КПД организма (25%)
            const joulesPerKcal = 4184;        // 1 ккал = 4184 Дж
            
            // Расчеты
            const distance = stepLength * steps / 1000;     // расстояние в км
            const timeSec = timeMin * 60;                    // время в секундах
            const speed = (distance / (timeMin / 60)).toFixed(2); // скорость в км/ч
            
            // Работа против силы тяжести за один шаг: A_шаг = m*g*h
            const workPerStep = weight * g * h;
            // Полная механическая работа за все шаги
            const totalWorkJoules = workPerStep * steps;
            
            // Мощность (Вт)
            const powerWatts = totalWorkJoules / timeSec;
            
            // Калории с учетом КПД
            const caloriesKcal = totalWorkJoules / joulesPerKcal / efficiency;
            
            // Отображаем результаты
            document.getElementById('stepLengthResult').innerHTML = stepLength.toFixed(2) + ' м';
            document.getElementById('distanceResult').innerHTML = distance.toFixed(3) + ' км';
            document.getElementById('speedResult').innerHTML = speed + ' км/ч';
            document.getElementById('workResult').innerHTML = totalWorkJoules.toFixed(0) + ' Дж';
            document.getElementById('powerResult').innerHTML = powerWatts.toFixed(1) + ' Вт';
            document.getElementById('caloriesResult').innerHTML = caloriesKcal.toFixed(1) + ' ккал';
            
            // Показываем блок с результатами
            document.getElementById('results').style.display = 'block';
            
            // Плавный скролл к результатам
            document.getElementById('results').scrollIntoView({ behavior: 'smooth', block: 'start' });
        }
        
        // Управление отображением поля для ручного ввода длины шага
        document.getElementById('manualStepCheckbox').addEventListener('change', function(e) {
            const row = document.getElementById('stepLengthRow');
            row.style.display = e.target.checked ? 'flex' : 'none';
        });
    </script>
</body>
</html>
