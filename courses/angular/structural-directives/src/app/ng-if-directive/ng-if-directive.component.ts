import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-ng-if-directive',
  template: `
  <h2 *ngIf=true>
    Welcome to {{ngIfName}}
  </h2>
  <h2 *ngIf=displayName>
    Conditional Variable
  </h2>

  <h2 *ngIf="false; else elseBlock1">
    Got To The If Case
  </h2>
  <ng-template #elseBlock1>
  <h2>
    Got To The Else Case
  </h2>
  </ng-template>

  <div *ngIf="false; then thenBlock; else elseBlock2"></div>

  <ng-template #thenBlock>
    <h2> Then Block </h2>
  </ng-template>
  
  <ng-template #elseBlock2>
    <h2> Else Block </h2>
  </ng-template>
  `,
  styles: []
})
export class NgIfDirectiveComponent implements OnInit {

  public ngIfName = "NG-IF-DIRECTIVE";
  public displayName = true;

  constructor() { }

  ngOnInit(): void {
  }

}
