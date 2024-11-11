export class MyComponent {
    people = [{ name: '', preferences: [] }];

    updatePreferences() {
        let names = [];
        for (let i = 0; i < {{ people }}; i++) {
            let name = document.getElementById(`name${i}`).value;
            if (name) {
                names.push(name);
            }
        }

        for (let i = 0; i < {{ people }}; i++; {
            let select = document.getElementById(`preferences${i}`);
            select.innerHTML = '<option value="no_preference">--</option>';
            // Add default option
            names.forEach((name, index) => {
                if (index !== i) {
                    // Exclude the name in the same row
                    let option = document.createElement('option');
                        option.value = name;
                        option.text = name;
                select.appendChild(option);
            }
        });
    }
}

    getPreferences(index: number) {
      return this.people
        .filter((_, i) => i !== index)
        .map(person => ({ name: person.name }));
    }
  }
