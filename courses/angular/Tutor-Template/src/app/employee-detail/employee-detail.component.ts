import { Component, OnInit } from '@angular/core';
import { EmployeeService } from '../employee.service';

@Component({
  selector: 'app-employee-detail',
  template: `
  <h2>
    <br>
    Welcome to {{eDName}}
  </h2>
  <ul *ngFor="let employee of employees">
    <li>{{employee.id}}. {{employee.name}} - {{employee.age}}</li>
  </ul>
  `,
  styles: []
})
export class EmployeeDetailComponent implements OnInit {

  public eDName = "EMPLOYEE-DETAIL";
  public employees = [];

  constructor(private _employeeService: EmployeeService) { }

  ngOnInit(): void {
    this.employees = this._employeeService.getEmployees();
  }

}
