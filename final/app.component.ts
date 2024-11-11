export class MyComponent {
    people = [{ name: '', preferences: [] }];

    updatePreferences() {
      // Logic to update preferences based on names
    }

    getPreferences(index: number) {
      return this.people
        .filter((_, i) => i !== index)
        .map(person => ({ name: person.name }));
    }
  }
