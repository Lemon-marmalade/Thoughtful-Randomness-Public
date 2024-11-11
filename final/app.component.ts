export class AppComponent {
    peoples: number;
    people = [{ name: '', preferences: [] }];

    updatePeople(): void {
        this.people = Array.from({ length: this.peoples }, () => ({ name: '', preferences: [] }));
      }

    updatePreferences(): void {
        const names: string[] = [];
        for (let i = 0; i < this.people.length; i++) {
            const name: string = (document.getElementById(`name${i}`) as HTMLInputElement).value;
            if (name) {
                names.push(name);
            }
        }

        for (let i = 0; i < this.people.length; i++) {
            const select: HTMLSelectElement = document.getElementById(`preferences${i}`) as HTMLSelectElement;
            select.innerHTML = '<option value="no_preference">--</option>';
            names.forEach((name, index) => {
                if (index !== i) {
                    const option: HTMLOptionElement = document.createElement('option');
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
