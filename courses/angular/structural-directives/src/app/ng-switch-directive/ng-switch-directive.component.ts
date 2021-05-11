import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-ng-switch-directive',
  template: `
  <h2>
    Welcome to {{ngSwitchName}}
  </h2>

    <div [ngSwitch]="color">
      <div *ngSwitchCase="'red'"> You picked the RED color </div>
      <div *ngSwitchCase="'green'"> You picked the GREEN color </div>
      <div *ngSwitchCase="'blue'"> You picked the BLUE color </div>
      <div *ngSwitchDefault> Pick Again </div>
    </div>
  `,
  styles: []
})
export class NgSwitchDirectiveComponent implements OnInit {

  public ngSwitchName = "NG-SWITCH-DIRECTIVE"
  public color = "green";

  constructor() { }

  ngOnInit(): void {
  }

}
